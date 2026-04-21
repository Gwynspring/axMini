/*
1. Prüfe ob filepath_ existiert
2. Wenn nicht → leere Datei erstellen → return true
3. Wenn ja → Datei öffnen und als JSON parsen
4. Variablen laden → engine_.AddVariable(...)
5. DSL Strings laden → Lexer → Parser → runtime_.AddStatements(...)
6. return true bei Erfolg, false bei Fehler*/

#include "axMini/PersistenceManager.hpp"
#include "axMini/Lexer.hpp"
#include "axMini/Logger.hpp"
#include "axMini/Parser.hpp"
#include "nlohmann/json.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>

bool PersistenceManager::Load() {
  if (!std::filesystem::exists(filepath_)) {
    std::filesystem::create_directories(filepath_.parent_path());
    std::ofstream ofs(filepath_);
    if (!ofs.is_open()) {
      Logger::Error("Coul not write to file " +
                    std::string(filepath_.filename()));
      return false;
    }
    nlohmann::json j = nlohmann::json::parse(R"(
  {
    "variables": [], 
    "dsl": []
  }
)");
    ofs << std::setw(4) << j << std::endl;
    ofs.close();
    Logger::Info(filepath_.lexically_relative(std::filesystem::current_path()));
    return true;
  }

  try {
    std::ifstream ifs(filepath_);
    nlohmann::json j;
    ifs >> j;

    for (const auto &var : j["variables"]) {
      std::string name = var["name"];
      if (name.empty())
        continue;

      std::optional<VariableType> type =
          Variable::VariableTypeFromString(var["type"]);
      if (!type.has_value())
        continue;

      auto val = var["value"];
      if (val.is_number_integer()) {
        Variable v(type.value(), name, val.get<int>());
        engine_.AddVariable(v);
      } else if (val.is_number_float()) {
        Variable v(type.value(), name, val.get<float>());
        engine_.AddVariable(v);
      } else if (val.is_boolean()) {
        Variable v(type.value(), name, val.get<bool>());
        engine_.AddVariable(v);
      }
    }

    for (const auto &dsl_str : j["dsl"]) {
      auto tokens = Lexer::Tokenize(dsl_str);
      runtime_.AddStatements(Parser::ParseIfStatement(tokens));
    }

    return true;

  } catch (const nlohmann::json::parse_error &e) {
    Logger::Error(
        std::format("message: {} \nexception id: {} \nbyte position of error",
                    e.what(), e.id, e.byte));
    return false;
  }
}

bool PersistenceManager::Save() {
  nlohmann::json j;
  j["variables"] = nlohmann::json::array();
  j["dsl"] = nlohmann::json::array();

  for (const auto &var : engine_.GetAllVariables()) {
    nlohmann::json j_var;
    std::visit([&j_var](auto val) { j_var["value"] = val; }, var.value);
    j_var["name"] = var.name;
    j_var["type"] = Variable::VariableTypeToString(var.variable_typ);
    j["variables"].push_back(j_var);
  }

  for (const auto &dsl_str : runtime_.GetDslStrings()) {
    j["dsl"].push_back(dsl_str);
  }

  std::ofstream ofs(filepath_);
  if (ofs.is_open()) {
    ofs << std::setw(4) << j;
    ofs.close();
  } else {
    Logger::Error("Could not open file for saving");
    return false;
  }
  Logger::Info("Saving to: " + filepath_.string());
  Logger::Info("Variables count: " +
               std::to_string(engine_.GetAllVariables().size()));
  return true;
}
