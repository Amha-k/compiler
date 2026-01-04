/*36.	Detect use of undeclared variables.
You must build a semantic pass that traverses an AST and flags any identifier used before declaration. Complexity includes handling forward declarations where allowed.

*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

enum class NodeType { VarDecl, VarUse, FuncDecl, FuncCall, Block };

struct ASTNode {
    NodeType type;
    std::string name;               
    std::string varType;             
    std::vector<ASTNode*> children;   
};

struct Symbol {
    std::string name;
    std::string type;
    bool declared;
    int scopeLevel;
};

class SymbolTable {
    std::vector<std::unordered_map<std::string, Symbol>> scopes;

public:
    void enterScope() { scopes.push_back({}); }
    void exitScope() { scopes.pop_back(); }

    bool addSymbol(const std::string& name, const std::string& type, bool declared = true) {
        if (scopes.back().count(name)) return false;
        scopes.back()[name] = {name, type, declared, (int)scopes.size()-1};
        return true;
    }

    Symbol* lookup(const std::string& name) {
        for (int i = (int)scopes.size()-1; i >= 0; --i) {
            if (scopes[i].count(name)) return &scopes[i][name];
        }
        return nullptr;
    }
};

void semanticCheck(ASTNode* node, SymbolTable& table) {
    if (!node) return;

    switch(node->type) {

        case NodeType::VarDecl:
            if (!table.addSymbol(node->name, node->varType)) {
                std::cerr << "Error: Redeclaration of variable " << node->name << "\n";
            }
            break;

        case NodeType::VarUse:
            {
                Symbol* sym = table.lookup(node->name);
                if (!sym || !sym->declared) {
                    std::cerr << "Error: Variable " << node->name << " used before declaration\n";
                }
            }
            break;

        case NodeType::FuncDecl:
           
            if (!table.addSymbol(node->name, "function")) {
                std::cerr << "Error: Redeclaration of function " << node->name << "\n";
            }
            break;

        case NodeType::Block:
            table.enterScope(); 
            break;
    }

 
    for (ASTNode* child : node->children) {
        semanticCheck(child, table);
    }

    if (node->type == NodeType::Block) {
        table.exitScope();
    }
}
