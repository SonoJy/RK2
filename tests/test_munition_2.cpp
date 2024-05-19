#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "munition2_just_class_def.cpp"

class Mock_Munition : public MunitionStore {
private:
    std::unique_ptr<WeaponCreator> weaponCreator_;
    std::unique_ptr<VehicleCreator> vehicleCreator_;
public:
Mock_Munition(std::unique_ptr<WeaponCreator>&& weaponCreator, std::unique_ptr<VehicleCreator>&& vehicleCreator) : MunitionStore(std::move(weaponCreator), std::move(vehicleCreator)) {}
MOCK_METHOD(void, Print, (WeaponType weaponType, VehicleType vehicleType), (const));
};

using ::testing::AtLeast;
TEST (Mock_Amunition2, pr) {
   Mock_Munition test(std::make_unique<WeaponCreator>(), std::make_unique<VehicleCreator>());
   EXPECT_CALL(test, Print(WeaponType::Knife, VehicleType::Horse)).Times(AtLeast(1));
   test.Print(WeaponType::Knife, VehicleType::Horse);
   EXPECT_CALL(test, Print(WeaponType::Knife, VehicleType::Horse)).Times(AtLeast(1));
   test.Print(WeaponType::Knife, VehicleType::Horse);
}

