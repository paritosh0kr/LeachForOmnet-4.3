//
// Generated file, do not edit! Created by opp_msgc 4.3 from TDMAMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "TDMAMessage_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(TDMAMessage);

TDMAMessage::TDMAMessage(const char *name, int kind) : ClusterMessage(name,kind)
{
    this->frames_var = 0;
    this->frameTime_var = 0;
    for (unsigned int i=0; i<103; i++)
        this->tdma_var[i] = 0;
}

TDMAMessage::TDMAMessage(const TDMAMessage& other) : ClusterMessage(other)
{
    copy(other);
}

TDMAMessage::~TDMAMessage()
{
}

TDMAMessage& TDMAMessage::operator=(const TDMAMessage& other)
{
    if (this==&other) return *this;
    ClusterMessage::operator=(other);
    copy(other);
    return *this;
}

void TDMAMessage::copy(const TDMAMessage& other)
{
    this->frames_var = other.frames_var;
    this->frameTime_var = other.frameTime_var;
    for (unsigned int i=0; i<103; i++)
        this->tdma_var[i] = other.tdma_var[i];
}

void TDMAMessage::parsimPack(cCommBuffer *b)
{
    ClusterMessage::parsimPack(b);
    doPacking(b,this->frames_var);
    doPacking(b,this->frameTime_var);
    doPacking(b,this->tdma_var,103);
}

void TDMAMessage::parsimUnpack(cCommBuffer *b)
{
    ClusterMessage::parsimUnpack(b);
    doUnpacking(b,this->frames_var);
    doUnpacking(b,this->frameTime_var);
    doUnpacking(b,this->tdma_var,103);
}

int TDMAMessage::getFrames() const
{
    return frames_var;
}

void TDMAMessage::setFrames(int frames)
{
    this->frames_var = frames;
}

int TDMAMessage::getFrameTime() const
{
    return frameTime_var;
}

void TDMAMessage::setFrameTime(int frameTime)
{
    this->frameTime_var = frameTime;
}

unsigned int TDMAMessage::getTdmaArraySize() const
{
    return 103;
}

int TDMAMessage::getTdma(unsigned int k) const
{
    if (k>=103) throw cRuntimeError("Array of size 103 indexed by %lu", (unsigned long)k);
    return tdma_var[k];
}

void TDMAMessage::setTdma(unsigned int k, int tdma)
{
    if (k>=103) throw cRuntimeError("Array of size 103 indexed by %lu", (unsigned long)k);
    this->tdma_var[k] = tdma;
}

class TDMAMessageDescriptor : public cClassDescriptor
{
  public:
    TDMAMessageDescriptor();
    virtual ~TDMAMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(TDMAMessageDescriptor);

TDMAMessageDescriptor::TDMAMessageDescriptor() : cClassDescriptor("TDMAMessage", "ClusterMessage")
{
}

TDMAMessageDescriptor::~TDMAMessageDescriptor()
{
}

bool TDMAMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<TDMAMessage *>(obj)!=NULL;
}

const char *TDMAMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int TDMAMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int TDMAMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *TDMAMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "frames",
        "frameTime",
        "tdma",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int TDMAMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "frames")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameTime")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "tdma")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *TDMAMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *TDMAMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int TDMAMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    TDMAMessage *pp = (TDMAMessage *)object; (void)pp;
    switch (field) {
        case 2: return 103;
        default: return 0;
    }
}

std::string TDMAMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    TDMAMessage *pp = (TDMAMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getFrames());
        case 1: return long2string(pp->getFrameTime());
        case 2: return long2string(pp->getTdma(i));
        default: return "";
    }
}

bool TDMAMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    TDMAMessage *pp = (TDMAMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setFrames(string2long(value)); return true;
        case 1: pp->setFrameTime(string2long(value)); return true;
        case 2: pp->setTdma(i,string2long(value)); return true;
        default: return false;
    }
}

const char *TDMAMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *TDMAMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    TDMAMessage *pp = (TDMAMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


