// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include "constants.h"
#include <iostream>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/motorcontrol/PWMMotorController.h>
#include <frc/motorcontrol/Talon.h>
#include <frc/XboxController.h>
#include "ctre/Phoenix.h"
#include <frc/AnalogGyro.h>
#include <frc/Timer.h>
#include <frc/Encoder.h>
#include "rev/CANSparkMax.h"
#include <frc/kinematics/ChassisSpeeds.h>

rev::CANSparkMax frontLeft(Constants::kFrontLeftDrive, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax frontRight(Constants::kFrontRightDrive, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax rearLeft(Constants::kRearLeftDrive, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax rearRight(Constants::kRearRightDrive, rev::CANSparkMax::MotorType::kBrushless);

rev::CANSparkMax leftShooter(Constants::kLeftShooter, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax rightShooter(Constants::kRightShooter, rev::CANSparkMax::MotorType::kBrushless);

TalonSRX meterWheel (Constants::kMeterWheel);

frc::MecanumDrive drivetrain(frontLeft, rearLeft, frontRight, rearRight);

frc::XboxController driverController(Constants::kJoystickChannel);

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
drivetrain.SetDeadband(0.1);


}
  

void Robot::TeleopPeriodic() {

  drivetrain.DriveCartesian (-driverController.GetRightY(), driverController.GetRightX(), -driverController.GetLeftY());
  
  if( driverController.GetXButton() )
  {
    leftShooter.Set(-1);
    rightShooter.Set(-1);
  }

  else if (driverController.GetAButton())
  {
    meterWheel.Set(ControlMode::PercentOutput, -.5);
  }

  else
  {
    leftShooter.Set(0);
    rightShooter.Set(0);
    meterWheel.Set(ControlMode::PercentOutput, 0);
  }




}


void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
