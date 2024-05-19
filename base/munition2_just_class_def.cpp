#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum class WeaponType { Knife, Gun, Missile };
enum class VehicleType { Horse, Tank, Spaceship };

struct Weapon { virtual ~Weapon() = default; virtual std::string Name() const = 0; };
struct Vehicle { virtual ~Vehicle() = default; virtual std::string Name() const = 0; };

struct Knife : public Weapon { std::string Name() const override { return "Knife"; } };
struct Gun : public Weapon { std::string Name() const override { return "Gun"; } };
struct Missile : public Weapon { std::string Name() const override { return "Missile"; } };

struct Horse : public Vehicle { std::string Name() const override { return "Horse"; } };
struct Tank : public Vehicle { std::string Name() const override { return "Tank"; } };
struct Spaceship : public Vehicle { std::string Name() const override { return "Spaceship"; } };

class WeaponCreator
{
public:
    virtual ~WeaponCreator() = default;

    virtual std::unique_ptr<Weapon> MakeWeapon(WeaponType type) const
    {
        switch (type)
        {
            case WeaponType::Knife:
                return std::make_unique<Knife>();
            case WeaponType::Gun:
                return std::make_unique<Gun>();
            case WeaponType::Missile:
                return std::make_unique<Missile>();
            default:
                return nullptr;
        }
    }
};

class FakeWeaponCreator : public WeaponCreator
{
public:
    std::unique_ptr<Weapon> MakeWeapon(WeaponType type) const override
    {
        switch (type)
        {
        case WeaponType::Knife:
            return std::make_unique<Missile>();
        default:
            return WeaponCreator::MakeWeapon(type);
        }
    }
};

class VehicleCreator
{
public:
    virtual ~VehicleCreator() = default;

    virtual std::unique_ptr<Vehicle> MakeVehicle(VehicleType type) const
    {
        switch (type)
        {
        case VehicleType::Horse:
            return std::make_unique<Horse>();
        case VehicleType::Tank:
            return std::make_unique<Tank>();
        case VehicleType::Spaceship:
            return std::make_unique<Spaceship>();
        default:
            return nullptr;
        }
    }
};

class FakeVehicleCreator : public VehicleCreator
{
public:
    std::unique_ptr<Vehicle> MakeVehicle(VehicleType type) const override
    {
        switch (type)
        {
        case VehicleType::Horse:
            return std::make_unique<Spaceship>();
        case VehicleType::Tank:
            return std::make_unique<Horse>();
        case VehicleType::Spaceship:
            return std::make_unique<Tank>();
        default:
            return nullptr;
        }
    }
};

class MunitionStore
{
public:
    MunitionStore(std::unique_ptr<WeaponCreator>&& weaponCreator, std::unique_ptr<VehicleCreator>&& vehicleCreator)
        : weaponCreator_(std::move(weaponCreator)), vehicleCreator_(std::move(vehicleCreator))
    {}

    void ChangeWeaponCreator(std::unique_ptr<WeaponCreator>&& creator) { weaponCreator_ = std::move(creator); }
    void ChangeVehicleCreator(std::unique_ptr<VehicleCreator>&& creator) { vehicleCreator_ = std::move(creator); }

    void Print(WeaponType weaponType, VehicleType vehicleType) const
    {
        std::cout << "---- Infomation ----" << std::endl;
        std::cout << "Weapon  : " << weaponCreator_->MakeWeapon(weaponType)->Name() << std::endl;
        std::cout << "Vehicle : " << vehicleCreator_->MakeVehicle(vehicleType)->Name() << std::endl;
        std::cout << "--------------------" << std::endl;
        std::cout << std::endl;
    }

private:
    std::unique_ptr<WeaponCreator> weaponCreator_;
    std::unique_ptr<VehicleCreator> vehicleCreator_;
};
