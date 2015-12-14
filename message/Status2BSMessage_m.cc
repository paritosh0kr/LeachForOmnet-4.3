//
// Generated file, do not edit! Created by opp_msgc 4.3 from Status2BSMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Status2BSMessage_m.h"

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




Register_Class(Status2BSMessage);

Status2BSMessage::Status2BSMessage(const char *name, int kind) : ClusterMessage(name,kind)
{
    this->energy_var = 0;
    this->status_var = 0;
    this->cluster_var = 0;
    this->xpos_var = 0;
    this->ypos_var = 0;
}

Status2BSMessage::Status2BSMessage(const Status2BSMessage& other) : ClusterMessage(other)
{
    copy(other);
}

Status2BSMessage::~Status2BSMessage()
{
}

Status2BSMessage& Status2BSMessage::operator=(const Status2BSMessage& other)
{
    if (this==&other) return *this;
    ClusterMessage::operator=(other);
    copy(other);
    return *this;
}

void Status2BSMessage::copy(const Status2BSMessage& other)
{
    this->energy_var = other.energy_var;
    this->status_var = other.status_var;
    this->cluster_var = other.cluster_var;
    this->xpos_var = other.xpos_var;
    this->ypos_var = other.ypos_var;
}

void Status2BSMessage::parsimPack(cCommBuffer *b)
{
    ClusterMessage::parsimPack(b);
    doPacking(b,this->energy_var);
    doPacking(b,this->status_var);
    doPacking(b,this->cluster_var);
    doPacking(b,this->xpos_var);
    doPacking(b,this->ypos_var);
}

void Status2BSMessage::parsimUnpack(cCommBuffer *b)
{
    ClusterMessage::parsimUnpack(b);
    doUnpacking(b,this->energy_var);
    doUnpacking(b,this->status_var);
    doUnpacking(b,this->cluster_var);
    doUnpacking(b,this->xpos_var);
    doUnpacking(b,this->ypos_var);
}

int Status2BSMessage::getEnergy() const
{
    return energy_var;
}

void Status2BSMessage::setEnergy(int energy)
{
    this->energy_var = energy;
}

int Status2BSMessage::getStatus() const
{
    return status_var;
}

void Status2BSMessage::setStatus(int status)
{
    this->status_var = status;
}

int Status2BSMessage::getCluster() const
{
    return cluster_var;
}

void Status2BSMessage::setCluster(int cluster)
{
    this->cluster_var = cluster;
}

int Status2BSMessage::getXpos() const
{
    return xpos_var;
}

void Status2BSMessage::setXpos(int xpos)
{
    this->xpos_var = xpos;
}

int Status2BSMessage::getYpos() const
{
    return ypos_var;
}

void Status2BSMessage::setYpos(int ypos)
{
    this->ypos_var = ypos;
}

class Status2BSMessageDescriptor : public cClassDescriptor
{
  public:
    Status2BSMessageDescriptor();
    virtual ~Status2BSMessageDescriptor();

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

Register_ClassDescriptor(Status2BSMessageDescriptor);

Status2BSMessageDescriptor::Status2BSMessageDescriptor() : cClassDescriptor("Status2BSMessage", "ClusterMessage")
{
}

Status2BSMessageDescriptor::~Status2BSMessageDescriptor()
{
}

bool Status2BSMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Status2BSMessage *>(obj)!=NULL;
}

const char *Status2BSMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Status2BSMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int Status2BSMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *Status2BSMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "energy",
        "status",
        "cluster",
        "xpos",
        "ypos",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int Status2BSMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "energy")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "cluster")==0) return base+2;
    if (fieldName[0]=='x' && strcmp(fieldName, "xpos")==0) return base+3;
    if (fieldName[0]=='y' && strcmp(fieldName, "ypos")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Status2BSMessageDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *Status2BSMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int Status2BSMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Status2BSMessage *pp = (Status2BSMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Status2BSMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Status2BSMessage *pp = (Status2BSMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getEnergy());
        case 1: return long2string(pp->getStatus());
        case 2: return long2string(pp->getCluster());
        case 3: return long2string(pp->getXpos());
        case 4: return long2string(pp->getYpos());
        default: return "";
    }
}

bool Status2BSMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Status2BSMessage *pp = (Status2BSMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setEnergy(string2long(value)); return true;
        case 1: pp->setStatus(string2long(value)); return true;
        case 2: pp->setCluster(string2long(value)); return true;
        case 3: pp->setXpos(string2long(value)); return true;
        case 4: pp->setYpos(string2long(value)); return true;
        default: return false;
    }
}

const char *Status2BSMessageDescriptor::getFieldStructName(void *object, int field) const
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
        NULL,
        NULL,
    };
    return (field>=0 && field<5) ? fieldStructNames[field] : NULL;
}

void *Status2BSMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Status2BSMessage *pp = (Status2BSMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


