//
//  Instrument.h
//  BoostMultiIndex
//
//  Created by Ganesh M on 29/9/12.
//  Copyright (c) 2012 Ganesh M. All rights reserved.
//

#ifndef BoostMultiIndex_Instrument_h
#define BoostMultiIndex_Instrument_h
class Instrument;
class InstrumentIdCompare;

struct InstrumentId {
    
    std::string id;
    std::string name;
    unsigned int value;
    
    explicit InstrumentId(std::string id = "",
                 std::string name = "",
                 unsigned int value = 0)
    : id(id), name(name), value(value)
    { }
    
    friend std::ostream& operator<<(std::ostream& os, const InstrumentId& i)
    {
        os << " (Instrument Id): " << i.id << ", " << i.name << "," << i.value << std::endl;
        return os;
    }
    
    bool operator==(const InstrumentId& rhs)
    {
        return (id == rhs.id && name == rhs.name && value == rhs.value);
    }
        
    bool operator==(const Instrument& rhs)
    {
        std::cout << "InstrumentId::operator== version 2\n";
        return true;
    }
    bool operator()(const Instrument& rhs)
    {
        std::cout << "InstrumentId::operator()version 2\n";
        return true;
    }
        bool operator()(const InstrumentId& rhs)
        {
            std::cout << "InstrumentId::operator()version 2\n";
            return true;
        }
};

class Instrument {
    
public:
    typedef boost::shared_ptr<Instrument> pointer;

public:

    Instrument(std::string externalid, std::string internalid)
    : m_ExternalId(externalid), m_InternalId(internalid)
    {
        
    }
    
    std::string ExternalId()  { return m_ExternalId; }
    std::string InternalId()  { return m_InternalId; }
    
    std::string ExternalId() const { return m_ExternalId; }
    std::string InternalId() const { return m_InternalId; }
    const InstrumentId& getId () const { return Id; }
    
    void SetId(const InstrumentId& Id)
    {
        this->Id.id = Id.id;
        this->Id.name = Id.name;
        this->Id.value = Id.value;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const pointer& i)
    {
        //std::cout << "pointer invoked ..\n";
        os << i.get()->ExternalId() << ", " << i.get()->InternalId()
            << " " << i.get()->getId();
        
        return os;
    }
        
    friend std::ostream& operator<<(std::ostream& os, const Instrument& i)
    {
                std::cout << "reference invoked ..\n";
        os << i.ExternalId() << ", " << i.InternalId() << " " << i.getId();
        return os;
    }
    
    bool operator==(const Instrument& rrh) const {

        std::cout << "Instrument::operator()" << std::endl;
        const InstrumentId& rh = rrh.getId();
        
        return (
                Id.id == rh.id && Id.value == rh.value);
    }
    
    bool operator==(const InstrumentIdCompare& rrh) const {
        
        std::cout << "Instrument::operator(InstrumentIdCompare)" << std::endl;
        return true;
    }
    
    bool operator()(const Instrument& rlh, const InstrumentId& rrh) const {
        std::cout << "InstrumentIdCompare::operator() " << std::endl;
        
        const InstrumentId& lh = rlh.getId();
        const InstrumentId& rh = rrh;
        
        if (lh.id < rh.id)
            return true;
        else if ( (lh.id == rh.id)
                 && lh.value < rh.value)
            return true;
        
        return false;
    }

private:
    std::string m_ExternalId;
    std::string m_InternalId;
    InstrumentId Id;
};

struct InstrumentIdCompare {
    
    bool operator()(const Instrument& rlh, const Instrument& rrh) const {
        std::cout << "InstrumentIdCompare::operator(1) " << std::endl;
        
        const InstrumentId& lh = rlh.getId();
        const InstrumentId& rh = rrh.getId();
        
        if (lh.id < rh.id)
            return true;
        else if ( (lh.id == rh.id)
                   && lh.value < rh.value)
            return true;

        return false;
    }
    
    bool operator()(const InstrumentId& rlh, const InstrumentId& rrh) const {
        std::cout << "InstrumentIdCompare::operator(2) " << std::endl;
        
        
        return true;
    }
    
    bool operator()(const InstrumentId& rlh, const Instrument& rrh) const {
        std::cout << "InstrumentIdCompare::operator(3) " << std::endl;
        const InstrumentId& lh = rlh;
        const InstrumentId& rh = rrh.getId();
        
        if (lh.id < rh.id)
            return true;
        else if ( (lh.id == rh.id)
                 && lh.value < rh.value)
            return true;
        
        return false;
    
            return true;
    }
    
    bool operator()(const Instrument& rlh, const InstrumentId& rrh) const {
        std::cout << "InstrumentIdCompare::operator(4) " << std::endl;
        
        const InstrumentId& lh = rlh.getId();
        const InstrumentId& rh = rrh;
        
        if (lh.id < rh.id)
            return true;
        else if ( (lh.id == rh.id)
                 && lh.value < rh.value)
            return true;
        
        return false;
    }


};

#endif
