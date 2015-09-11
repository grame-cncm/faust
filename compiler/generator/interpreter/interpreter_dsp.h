

#include "faust/audio/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

#include "garbageable.hh"


// Interpreter

#define push_real(val) real_stack[real_stack_index++] = val; 
#define push_int(val) int_stack[int_stack_index++] = val;

#define pop_real() real_stack[real_stack_index--];
#define pop_int() int_stack[int_stack_index--];

struct Instruction : public virtual Garbageable {

    enum Opcode { kRealValue, kIntValue, kLoadReal, kLoadInt, kStoreReal, kStoreInt,
        kCastReal, kCastInt, kIfInt, kIfReal, 
        kAddReal, kAddInt, kSubReal, kSubInt, kMultReal, kMulInt, kDivReal, kDivInt,
        kRemInt, kLshInt, kRshInt, kGTInt, kLTInt, kGEInt, kLEInt, kEQInt, kNEInt, kGTReal, kLTReal, kGEReal, kLEReal, kEQReal, kNEReal,
        kANDInt, kORInt, kXORInt,
        kSin, kCos };
     
};

struct BlockInstruction : public Instruction {

     list<Instruction*> fInstructions;
     
};

template <class T>
struct BasicInstruction : public Instruction {

    int fOffset;
    Opcode fOpcode;
    int fIntValue;
    T fRealValue;
    
    BlockInstruction* fbranch1;
    BlockInstruction* fbranch2;
    
    BasicInstruction(int opcode, int offset = 0) : fOpcode(code), fOffset(offset) {}
    BasicInstruction(int opcode, int offset = 0) : fOpcode(code), fOffset(offset) {}
     
};

template <class T>
struct Interpreter {

    T* fRealHeap;
    int* fIntHeap;
    
    int fRealStackSize;
    int fIntStackSize;
    
    BlockInstruction fComputeBlockInstructions;
    
    /*
    void PrintBlock()
    {
        list<Instruction*>::const_iterator it;
          
        for (it = instructions->fBlock.begin(); it != instructions->fBlock.end(); it++) {
        
            switch ((*it)->fOpcode) {
            
                // Number operations
                case Instruction::kRealValue;
                    cout << "kRealValue " << (*it)->fRealValue << endl;
                    break;
                    
                case Instruction::kIntValue;
                    cout << "kIntValue " << (*it)->fIntValue << endl;
                    break;
                
                // Memory operations
                case Instruction::kLoadReal;
                    cout << "kLoadReal : offset " << (*it)->fOffset << endl;
                    break;
                    
                case Instruction::kLoadInt;
                    cout << "kLoadInt : offset " << (*it)->fOffset << endl;
                    break;
                    
                case Instruction::kStoreReal;
                    cout << "kStoreReal : offset " << (*it)->fOffset << "= " << pop_real()  << endl;
                    break;
                    
                case Instruction::kStoreInt;
                    out << "kStoreInt : offset " << (*it)->fOffset << "= " << pop_int()  << endl;
                    break;
                  
                // Cast operations
                case Instruction::kCastReal;
                    push_real(T(pop_int()));
                    break;
                    
                case Instruction::kCastInt;
                    push_int(int(pop_real()));
                    break;
                    
                // Select operation
                case Instruction::kIfInt;
                    if (pop_int()) {
                        push_int(ExecuteInt((*it)->fbranch1));
                    } else {
                        push_int(ExecuteInt((*it)->fbranch2));
                    }
                    break;
                
                case Instruction::kIfReal;
                    if (pop_int()) {
                        push_real(ExecuteReal((*it)->fbranch1));
                    } else {
                        push_real(ExecuteReal((*it)->fbranch2));
                    }
                    break;
                    
                // Standard math operations
                case Instruction::kAddReal;
                    push_real(pop_real() + pop_real());
                    break;
                    
                case Instruction::kAddInt;
                    push_int(pop_int() + pop_int());
                    break;
                    
                case Instruction::kSubReal;
                    push_real(pop_real() - pop_real());
                    break;
                    
                case Instruction::kSubInt;
                    push_int(pop_int() - pop_int());
                    break;
                    
                case Instruction::kMultReal;
                    push_real(pop_real() * pop_real());
                    break;
                    
                case Instruction::kMultInt;
                    push_int(pop_int() * pop_int());
                    break;
                    
                case Instruction::kDivReal;
                    push_real(pop_real() / pop_real());
                    break;
                    
                case Instruction::kDivInt;
                    push_int(pop_int() / pop_int());
                    break;
                   
                // Other Math operations
                case Instruction::kSin;
                    push_real(sin(pop_real()));
                    break;
                    
                case Instruction::kCos;
                    push_real(cos(pop_real()));
                    break;
        
            }
        }
    }
    */
    
    /*
        - Offset in arrays in HEAP can be precomputed when visiting FIR
        - real_stack and int_stack size can be computed when visiting FIR
    
    */
   
    void ExecuteBlock(BlockInstruction* block, in& res_int, T& res_real, bool is_int_res)
    {
        list<Instruction*>::const_iterator it;
         
        T val1_real;
        T val2_real;
        
        int val1_int;
        int val2_int;
        
        for (it = block->fInstructions.begin(); it != block->fInstructions.end(); it++) {
        
            switch ((*it)->fOpcode) {
            
                // Number operations
                case Instruction::kRealValue1;
                    val1_real = (*it)->fRealValue;
                    break;
                    
                case Instruction::kRealValue2;
                    val2_real = (*it)->fRealValue;
                    break;
                    
                case Instruction::kIntValue1;
                    val1_int = (*it)->fIntValue;
                    break;
                    
                 case Instruction::kIntValue2;
                    val2_int = (*it)->fIntValue;
                    break;
                
                // Memory operations
                case Instruction::kLoadReal1;
                    val1_real = fRealHeap[(*it)->fOffset];
                    break;
                    
                case Instruction::kLoadReal2;
                    val2_real = fRealHeap[(*it)->fOffset];
                    break;
                    
                case Instruction::kLoadInt1;
                    val1_int = fIntHeap[(*it)->fOffset];
                    break;
                    
                case Instruction::kLoadInt2;
                    val2_int = fIntHeap[(*it)->fOffset];
                    break;
                    
                case Instruction::kStoreReal1;
                    fRealHeap[(*it)->fOffset] = val1_real;
                    break;
                    
                case Instruction::kStoreReal2;
                    fRealHeap[(*it)->fOffset] = val2_real;
                    break;
                    
                case Instruction::kStoreInt1;
                    fIntHeap[(*it)->fOffset] = val1_int;
                    break;
                    
                case Instruction::kStoreInt2;
                    fIntHeap[(*it)->fOffset] = val2_int;
                    break;
                  
                // Cast operations
                case Instruction::kCastReal;
                    val1_real = T(val1_int);
                    break;
                    
                case Instruction::kCastInt;
                    val1_int1 = int(val1_real1);
                    break;
                    
                // Select operation
                case Instruction::kIfInt;
                    val1_int  = (val1_int1 ? ExecuteInt((*it)->fbranch1) : ExecuteInt((*it)->fbranch2));
                    break;
                
                case Instruction::kIfReal;
                    val1_real  = (val1_int1 ? ExecuteReal((*it)->fbranch1) : ExecuteReal((*it)->fbranch2));
                    break;
                    
                // Standard math operations
                case Instruction::kAddReal;
                    val1_real = val1_real + val2_real;
                    break;
                    
                case Instruction::kAddInt;
                    val1_int = val1_int  + val2_int;
                    break;
                    
                case Instruction::kSubReal;
                    val1_real = val1_real - val2_real;
                    break;
                    
                case Instruction::kSubInt;
                    val1_int = val1_int - val2_int;
                    break;
                    
                case Instruction::kMultReal;
                    val1_real = val1_real * val2_real;
                    break;
                    
                case Instruction::kMultInt;
                    val1_int = val1_int * val2_int;
                    break;
                    
                case Instruction::kDivReal;
                    val1_real = val1_real / val2_real;
                    break;
                    
                case Instruction::kDivInt;
                    val1_int = val1_int / val2_int;
                    break;
                    
                case Instruction::kRemInt;
                    val1_int = val1_int % val2_int;
                    break;
                
                // Shift operation
                case Instruction::kLshInt;
                    val1_int = val1_int << val2_int;
                    break;
                    
                case Instruction::kRshInt;
                    val1_int = val1_int >> val2_int;
                    break;
                 
                // Comparaison Int
                case Instruction::kGTInt;
                    val1_int = val1_int > val2_int;
                    break;
                    
                case Instruction::kLTInt;
                    val1_int = val1_int < val2_int;
                    break;
                    
                case Instruction::kGEInt;
                    val1_int = val1_int >= val2_int;
                    break;
                    
                case Instruction::kLEInt;
                    val1_int = val1_int <= val2_int;
                    break;
                
                case Instruction::kEQInt;
                    val1_int = val1_int == val2_int;
                    break;
                    
                case Instruction::kNEInt;
                    val1_int = val1_int != val2_int;
                    break;
                    
                // Comparaison Real    
                case Instruction::kGTReal
                    val1_int = val1_real > val2_real;
                    break;
                    
                case Instruction::kLTReal;
                    val1_int = val1_real < val2_real;
                    break;
                    
                case Instruction::kGEReal;
                    val1_int = val1_real >= val2_real;
                    break;
                    
                case Instruction::kLEReal;
                    val1_int = val1_real <= val2_real;
                    break;
                
                case Instruction::kEQReal;
                    val1_int = val1_real == val2_real;
                    break;
                    
                case Instruction::kNEReal;
                    val1_int = val1_real != val2_real;
                    break;
                
                // Logical operations
                case Instruction::kANDInt;
                    val1_int = val1_int & val2_int;
                    break;
                 
                case Instruction::kORInt;
                    val1_int = val1_int | val2_int;
                    break;
                    
                case Instruction::kXORInt;
                    val1_int = val1_int ^  val2_int;
                    break;
                   
                // Other Math operations
                case Instruction::kSin;
                    val1_real = sinf(val1_real);
                    break;
                    
                case Instruction::kCos;
                    val1_real = cosf(val1_real);
                    break;
        
            }
        }
        
        if (is_int_res) {
            res_int = pop_int();
        } else {
            res_real = pop_real();
        }
    }
    
    int ExecuteBlockInt(BlockInstruction* block)
    {
        int res_int;
        T res_real;
        ExecuteBlock(block, res_int, res_real, true);
        return res_int;
    }
    
    void ExecuteBlockReal(BlockInstruction* block)
    {
        int res_int;
        T res_real;
        ExecuteBlock(block, res_int, res_real, false);
        return res_real;
    }
    
    Interpreter(int real_heap_size, int int_heap_size)
    {
        fRealHeap = new T[real_heap_size];
        fIntHeap = new int[int_heap_size];
    }
    
    virtual ~Interpreter()
    {
        delete [] fRealBuffer;
        delete [] fIntBuffer;
    }
 
};

template <class T>
class interperter_dsp : public dsp, public Interpreter {
	
    protected:
        
        int fSamplingFreq;
        
        int fNumInputs;
        int fNumOutputs;
        
        T** fInputs;
        T** fOutputs;
  	
    public:
      
        interperter_dsp(int inputs, int ouputs, int real_heap_size, int int_heap_size) 
            : Interpreter(real_heap_size, int_heap_size)
        {
            fInputs = new T*[inputs];
            fOutputs = new T*[ouputs];
        }
        
        virtual ~interperter_dsp()
        {
            delete [] fRealBuffer;
            delete [] fIntBuffer;
            
            delete [] fInputs;
            delete [] fOutputs;
        }
        
        void static metadata(Meta* m) 
        { 
            
        }

        virtual int getNumInputs() 
        {
            return fNumInputs;
        }
        
        virtual int getNumOutputs() 
        {
            return fNumOutputs;
        }
        
        virtual int getInputRate(int channel) 
        {
            return -1;
        }
        
        virtual int getOutputRate(int channel) 
        {
            return -1;
        }
        
        static void classInit(int samplingFreq) 
        {}
        
        virtual void instanceInit(int samplingFreq) 
        {
            fSamplingFreq = samplingFreq;
            
            int int_val;
            T real_val;
            
            // Execute init instructions 
            ExecuteBlock(fInitInstructions, int_val, real_val);
        }
        
        virtual void init(int samplingFreq) 
        {
            classInit(samplingFreq);
            instanceInit(samplingFreq);
        }
        
        virtual void buildUserInterface(UI* interface) 
        {
        
        }
        
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            // Prepare in/out buffers
            for (int i = 0; i < fNumInputs; i++) {
                fInputs[i] = inputs[i];
            }
            for (int i = 0; i < fNumInputs; i++) {
                fOutputs[i] = outputs[i];
            }
            
            int int_val;
            T real_val;
            
            // Execute instructions before the DSP loop
            Execute(fRealHeap, fIntHeap, int_val, real_val, fComputeBlockInstructions);
            
            // Execute the DSP loop
            for (int i = 0; i < count; i++) {
                ExecuteBlockReal(fDAGBlock);
            }
       }
	
};

