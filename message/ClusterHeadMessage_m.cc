//
// Generated file, do not edit! Created by opp_msgc 4.3 from ClusterHeadMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "ClusterHeadMessage_m.h"

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




Register_Class(ClusterHeadMessage);

ClusterHeadMessage::ClusterHeadMessage(const char *name, int kind) : ClusterMessage(name,kind)
{
    for (unsigned int i=0; i<103; i++)
        this->cHead_var[i] = 0;
}

ClusterHeadMessage::ClusterHeadMessage(const ClusterHeadMessage& other) : ClusterMessage(other)
{
    copy(other);
}

ClusterHeadMessage::~ClusterHeadMessage()
{
}

ClusterHeadMessage& ClusterHeadMessage::operator=(const ClusterHeadMessage& other)
{
    if (this==&other) return *this;
    ClusterMessage::operator=(other);
    copy(other);
    return *this;
}

void ClusterHeadMessage::copy(const ClusterHeadMessage& other)
{
    for (unsigned int i=0; i<103; i++)
        this->cHead_var[i] = other.cHead_var[i];
}

void ClusterHeadMessage::parsimPack(cCommBuffer *b)
{
    ClusterMessage::parsimPack(b);
    doPacking(b,this->cHead_var,103);
}

void ClusterHeadMessage::parsimUnpack(cCommBuffer *b)
{
    ClusterMessage::parsimUnpack(b);
    doUnpacking(b,this->cHead_var,103);
}

unsigned int ClusterHeadMessage::getCHeadArraySize() const
{
    return 103;
}

int ClusterHeadMessage::getCHead(unsigned int k) const
{
    if (k>=103) throw cRuntimeError("Array of size 103 indexed by %lu", (unsigned long)k);
    return cHead_var[k];
}

void ClusterHeadMessage::setCHead(unsigned int k, int cHead)
{
    if (k>=103) throw cRuntimeError("Array of size 103 indexed by %lu", (unsigned long)k);
    this->cHead_var[k] = cHead;
}

class ClusterHeadMessageDescriptor : public cClassDescriptor
{
  public:
    ClusterHeadMessageDescriptor();
    virtual ~ClusterHeadMessageDescriptor();

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

Register_ClassDescriptor(ClusterHeadMessageDescriptor);

ClusterHeadMessageDescriptor::ClusterHeadMessageDescriptor() : cClassDescriptor("ClusterHeadMessage", "ClusterMessage")
{
}

ClusterHeadMessageDescriptor::~ClusterHeadMessageDescriptor()
{
}

bool ClusterHeadMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ClusterHeadMessage *>(obj)!=NULL;
}

const char *ClusterHeadMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ClusterHeadMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int ClusterHeadMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *ClusterHeadMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "cHead",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int ClusterHeadMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cHead")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ClusterHeadMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *ClusterHeadMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int ClusterHeadMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ClusterHeadMessage *pp = (ClusterHeadMessage *)object; (void)pp;
    switch (field) {
        case 0: return 103;
        default: return 0;
    }
}

std::string ClusterHeadMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ClusterHeadMessage *pp = (ClusterHeadMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCHead(i));
        default: return "";
    }
}

bool ClusterHeadMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ClusterHeadMessage *pp = (ClusterHeadMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setCHead(i,string2long(value)); return true;
        default: return false;
    }
}

const char *ClusterHeadMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *ClusterHeadMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ClusterHeadMessage *pp = (ClusterHeadMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


