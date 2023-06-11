class Vehicle:
    def __init__(self, model_year, kilometers):
        self.model_year = model_year
        self.kilometers = kilometers

    def drive(self, new_kilometers):
        self.kilometers += new_kilometers
        print(f"After {new_kilometers} kilometers, odometer reading is {self.kilometers}")

class Car(Vehicle):
    def __init__(self, model_year, kilometers, number_of_doors):
        super().__init__(model_year, kilometers)
        self.number_of_doors = number_of_doors

class Motorcycle(Vehicle):
    def __init__(self, model_year, kilometers):
        super().__init__(model_year, kilometers)

    def ride_on_the_rear_wheel(self):
        print("Motorcycle rides on the rear wheel.")

if __name__ == "__main__":
    
    print("--- ElectricBike ---")
    ElectricBike = Vehicle(2018, 0)
    ElectricBike.drive(47)
    ElectricBike.drive(35)

    print("\n--- Car ---")
    car = Car(2020, 150, 5)
    print(f"Number of doors: {car.number_of_doors}")
    car.drive(23)

    print("\n--- Motorcycle ---")
    motor = Motorcycle(2019, 0)
    motor.drive(54)
    motor.ride_on_the_rear_wheel()
    motor.drive(2)

