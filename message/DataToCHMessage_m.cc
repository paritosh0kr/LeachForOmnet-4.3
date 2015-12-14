//
// Generated file, do not edit! Created by opp_msgc 4.3 from DataToCHMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "DataToCHMessage_m.h"

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




Register_Class(DataToCHMessage);

DataToCHMessage::DataToCHMessage(const char *name, int kind) : ClusterMessage(name,kind)
{
    this->newSun_var = 0;
    this->data_var = 0;
}

DataToCHMessage::DataToCHMessage(const DataToCHMessage& other) : ClusterMessage(other)
{
    copy(other);
}

DataToCHMessage::~DataToCHMessage()
{
}

DataToCHMessage& DataToCHMessage::operator=(const DataToCHMessage& other)
{
    if (this==&other) return *this;
    ClusterMessage::operator=(other);
    copy(other);
    return *this;
}

void DataToCHMessage::copy(const DataToCHMessage& other)
{
    this->newSun_var = other.newSun_var;
    this->data_var = other.data_var;
}

void DataToCHMessage::parsimPack(cCommBuffer *b)
{
    ClusterMessage::parsimPack(b);
    doPacking(b,this->newSun_var);
    doPacking(b,this->data_var);
}

void DataToCHMessage::parsimUnpack(cCommBuffer *b)
{
    ClusterMessage::parsimUnpack(b);
    doUnpacking(b,this->newSun_var);
    doUnpacking(b,this->data_var);
}

int DataToCHMessage::getNewSun() const
{
    return newSun_var;
}

void DataToCHMessage::setNewSun(int newSun)
{
    this->newSun_var = newSun;
}

int DataToCHMessage::getData() const
{
    return data_var;
}

void DataToCHMessage::setData(int data)
{
    this->data_var = data;
}

class DataToCHMessageDescriptor : public cClassDescriptor
{
  public:
    DataToCHMessageDescriptor();
    virtual ~DataToCHMessageDescriptor();

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

Register_ClassDescriptor(DataToCHMessageDescriptor);

DataToCHMessageDescriptor::DataToCHMessageDescriptor() : cClassDescriptor("DataToCHMessage", "ClusterMessage")
{
}

DataToCHMessageDescriptor::~DataToCHMessageDescriptor()
{
}

bool DataToCHMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DataToCHMessage *>(obj)!=NULL;
}

const char *DataToCHMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DataToCHMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int DataToCHMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *DataToCHMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "newSun",
        "data",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DataToCHMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "newSun")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DataToCHMessageDescriptor::getFieldTypeString(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *DataToCHMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DataToCHMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DataToCHMessage *pp = (DataToCHMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DataToCHMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DataToCHMessage *pp = (DataToCHMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNewSun());
        case 1: return long2string(pp->getData());
        default: return "";
    }
}

bool DataToCHMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DataToCHMessage *pp = (DataToCHMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setNewSun(string2long(value)); return true;
        case 1: pp->setData(string2long(value)); return true;
        default: return false;
    }
}

const char *DataToCHMessageDescriptor::getFieldStructName(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *DataToCHMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DataToCHMessage *pp = (DataToCHMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


