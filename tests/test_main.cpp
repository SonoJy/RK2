#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "munition_just_class_def.cpp"

class Mock_Munition : public MunitionStore {
private:
    std::unique_ptr<WeaponCreator> weaponCreator_;
    std::unique_ptr<VehicleCreator> vehicleCreator_;
public:
Mock_Munition(std::unique_ptr<WeaponCreator>&& weaponCreator, std::unique_ptr<VehicleCreator>&& vehicleCreator) : MunitionStore(std::move(weaponCreator), std::move(vehicleCreator)) {}
MOCK_METHOD(void, Print, (), (const));
};

using ::testing::AtLeast;
TEST (Mock_Amunition, pr) {
   Mock_Munition test(std::move(std::make_unique<KnifeCreator>()), std::move(std::make_unique<HorseCreator>()));
   EXPECT_CALL(test, Print()).Times(AtLeast(1));
   test.Print();
   test.ChangeWeaponCreator(std::make_unique<GunCreator>());
   EXPECT_CALL(test, Print()).Times(AtLeast(1));
   test.Print();
}
