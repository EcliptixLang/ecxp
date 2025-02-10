#include "compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::compile(std::shared_ptr<AST::ExprAST>& astNode){
	
		AST::Nodes type = astNode->getType();
		switch (type){
			case Nodes::Program:
				return CProgram(astNode);
			case Nodes::Call:
				return CCall(astNode);
			case Nodes::String:
				return CString(astNode);
			case Nodes::Identifier:
				return CIdent(astNode);
			case Nodes::Number:
				return CNumber(astNode);
			case Nodes::Variable:
				return CVariable(astNode);
			case Nodes::Binary:
				return CBinary(astNode);
			case Nodes::Array:
				return CArray(astNode);
			case Nodes::Member:
				return CMember(astNode);
			case Nodes::If:
				return CIf(astNode);
			case Nodes::Equality:
				return CEqu(astNode);
			case Nodes::Skip:
				code += "continue;\n";
				return;
			case Nodes::ShellCmd:{
				AST::ShellCMD* cmd = dynamic_cast<AST::ShellCMD*>(astNode.get());
				if(!libs["bun"]){
					libs["bun"] = true;
				}

				code += "bun.$`" + cmd->cmd + "`\n";
			} break;
			case Nodes::Break:
				code += "break;\n";
			case Nodes::Function:
				return CFunction(astNode);
			case Nodes::Assignment:
				return CAssignment(astNode);
			break;
			case Nodes::While:
				return CWhile(astNode);
			case Nodes::Object:
				return CObject(astNode);
			break;
			case Nodes::Return: {
				AST::ReturnExpr* number = dynamic_cast<AST::ReturnExpr*>(astNode.get());
				code += "return ";
				compile(number->value);
			} break;
			default:
				std::cerr 
					<< "This AST Node is not yet set up for interpretation.\n" 
					<< "- Type: " << AST::stringifyAST(type) << "\n";
				exit(1);
		}
}