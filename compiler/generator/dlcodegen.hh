#pragma once
#include <string>

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
    virtual std::string read(const std::string& index) const;
    virtual std::string write(const std::string& exp) const;
};
