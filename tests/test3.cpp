#include <gtest/gtest.h>
#include "munition2_just_class_def.cpp"

TEST (Mock_Methods, pr) {
   testing::internal::CaptureStdout(); 
   MunitionStore store(std::make_unique<WeaponCreator>(), std::make_unique<VehicleCreator>());
   store.Print(WeaponType::Knife, VehicleType::Horse);
   store.ChangeWeaponCreator(std::make_unique<FakeWeaponCreator>());
   store.Print(WeaponType::Knife, VehicleType::Horse);
   store.ChangeVehicleCreator(std::make_unique<FakeVehicleCreator>());
   store.Print(WeaponType::Knife, VehicleType::Horse);
  EXPECT_EQ(testing::internal::GetCapturedStdout(), "---- Infomation ----\nWeapon  : Knife\nVehicle : Horse\n--------------------\n\n---- Infomation ----\nWeapon  : Missile\nVehicle : Horse\n--------------------\n\n---- Infomation ----\nWeapon  : Missile\nVehicle : Spaceship\n--------------------\n\n");
}

