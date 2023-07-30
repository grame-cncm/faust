#pragma once
#include <string>

/*
    // globalDeclare()
    float fVec0State[32];

    virtual void instanceClear()
    {
        // globalInit()
        for (int l0 = 0; l0 < 32; l0 = l0 + 1) {
            fVec0State[l0] = 0.0f;
        }
    }

        // localDeclare()
        float       fVec0cache[BLOCK_SIZE + 32];              // local copy of the delay line
        float      *fVec0     = fVec0cache + BLOCK_SIZE - 1;  // pointer to the delay line in the local copy

        // saved to local delay line
        //
        // copyGlobalToLocal()
        for (int j = 1; j < 32; j++) {
            fVec0[j] = fVec0State[j];
        }
            // write(exp)
            fVec0[0]     = fTemp0;

            for (int j = 1; j < 32; ++j) {
                // read(index)
                fSum += fCoef[j] * fVec0[j];
            }

            // advance1()
            --fVec0;

        // local to save delay line
        // copyLocalToGlobal()
        for (int j = 1; j < 32; j++) {
            fVec0State[j] = fVec0[j];
        }


*/

class DlCodeGen {
    std::string fDlType;
    std::string fDlName;
    int         fBlockSize;
    int         fDlMaxDelay;
    bool        fMono;

   public:
    DlCodeGen(const std::string& dlType, const std::string& dlName, int blockSize, int dlSize, bool mono)
        : fDlType(dlType), fDlName(dlName), fBlockSize(blockSize), fDlMaxDelay(dlSize), fMono(mono)
    {
    }
    virtual ~DlCodeGen() = default;

    virtual std::string globalDeclare() const;
    virtual std::string globalInit() const;
    virtual std::string localDeclare() const;
    virtual std::string PointerSetup() const;
    virtual std::string copyGlobalToLocal() const;
    virtual std::string copyLocalToGlobal() const;
    virtual std::string advance() const;
    virtual std::string read(std::string index) const;
    virtual std::string write(std::string exp) const;
};