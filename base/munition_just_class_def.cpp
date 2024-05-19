#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Weapon { virtual ~Weapon() = default; virtual std::string Name() const = 0; };
struct Vehicle { virtual ~Vehicle() = default; virtual std::string Name() const = 0; };

struct Knife : public Weapon { std::string Name() const override { return "Knife"; } };
struct Gun : public Weapon { std::string Name() const override { return "Gun"; } };
struct Missile : public Weapon { std::string Name() const override { return "Missile"; } };

struct Horse : public Vehicle { std::string Name() const override { return "Horse"; } };
struct Tank : public Vehicle { std::string Name() const override { return "Tank"; } };
struct Spaceship : public Vehicle { std::string Name() const override { return "Spaceship"; } };

struct WeaponCreator
    { virtual ~WeaponCreator() = default; virtual std::unique_ptr<Weapon> MakeWeapon() const = 0; };
struct VehicleCreator
    { virtual ~VehicleCreator() = default; virtual std::unique_ptr<Vehicle> MakeVehicle() const = 0; };

struct KnifeCreator : public WeaponCreator
    { std::unique_ptr<Weapon> MakeWeapon() const override { return std::make_unique<Knife>(); } };
struct GunCreator : public WeaponCreator
    { std::unique_ptr<Weapon> MakeWeapon() const override { return std::make_unique<Gun>(); } };
struct MissileCreator : public WeaponCreator
    { std::unique_ptr<Weapon> MakeWeapon() const override { return std::make_unique<Missile>(); } };

struct HorseCreator : public VehicleCreator
    { std::unique_ptr<Vehicle> MakeVehicle() const override { return std::make_unique<Horse>(); } };
struct TankCreator : public VehicleCreator
    { std::unique_ptr<Vehicle> MakeVehicle() const override { return std::make_unique<Tank>(); } };
struct SpaceshipCreator : public VehicleCreator
    { std::unique_ptr<Vehicle> MakeVehicle() const override { return std::make_unique<Spaceship>(); } };

class MunitionStore
{
public:
    MunitionStore(std::unique_ptr<WeaponCreator>&& weaponCreator, std::unique_ptr<VehicleCreator>&& vehicleCreator)
        : weaponCreator_(std::move(weaponCreator)), vehicleCreator_(std::move(vehicleCreator))
    {}

    void ChangeWeaponCreator(std::unique_ptr<WeaponCreator>&& creator) { weaponCreator_ = std::move(creator); }
    void ChangeVehicleCreator(std::unique_ptr<VehicleCreator>&& creator) { vehicleCreator_ = std::move(creator); }

    void Print() const
    {
        std::cout << "---- Infomation ----" << std::endl;
        std::cout << "Weapon  : " << weaponCreator_->MakeWeapon()->Name() << std::endl;
        std::cout << "Vehicle : " << vehicleCreator_->MakeVehicle()->Name() << std::endl; 
        std::cout << "--------------------" << std::endl;
        std::cout << std::endl;
    }

private:
    std::unique_ptr<WeaponCreator> weaponCreator_;
    std::unique_ptr<VehicleCreator> vehicleCreator_;
};