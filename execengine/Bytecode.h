
#ifndef execengine_Bytecode_h
#define execengine_Bytecode_h

#include <string>

namespace execengine {

    class Object;
    
    enum BCOperation {
        VariableLoad,
        VaraibleStore,
        MessegeSend,
        ConstantLoad,
        Return
    };
    
    typedef BCRegister Object*;
    
    struct BCInstruction {
    public: 
        BCInstruction(unsigned int op) : opCode(op) { }
        unsigned int opCode; 
        // Here goes arguments registers
    };
    
    struct BCInstructionVariableLoad : public BCInstruction {
    public:
        BCInstructionVariableLoad(unsigned int res, string* var) 
            : BCInstruction(VariableLoad), resultRegister(res), varName(var) { }
        unsigned int resultRegister;
        string* varName
    };
    
    struct BCInstructionVariableStore : public BCInstruction {
    public:
        BCInstructionVariableStore(unsigned int src, string* var) 
            : BCInstruction(VariableStore), sourceRegister(src), varName(var) { }
        unsigned int sourceRegister;
        string* varName
    };
    
    struct BCInstructionMessageSend : public BCInstruction {
    public:
        BCInstructionMessageSend(unsigned int src, string* var) 
            : BCInstruction(MessegeSend), sourceRegister(src), varName(var) { }
        unsigned int subjectRegister;
        unsigned int resultRegister;
        unsigned int argsCount;
        string* methodName;
        unsigned int* argsRegisters;
        
    };
    
    struct BCInstructionConstantLoad : public BCInstruction {
    public:
        BCInstructionVariableLoad()
        unsigned int resultRegister;
        string* varName
    };
    
    

#endif // execengine_Bytecode_h
