
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def walk(self):
        print(f"{self.name} ({self.age}) walks")

    def say(self, message):
        print(f"{self.name} says: {message}")

class Superhero(Person):
    def __init__(self, name, age, secret_identity):
        super().__init__(name, age)
        self.secret_identity = secret_identity

    def fly(self):
        print(f"{self.name} (aka {self.secret_identity}) is flying.")

    def use_super_sight(self):
        print(f"{self.name} (aka {self.secret_identity}) uses super sight.")

    def walk(self, user_power = False):
        if user_power:
            print(f"{self.name} (aka {self.secret_identity}) uses extra-speed running.")
        else:
            super().walk()

if __name__ == "__main__":
    
    print("--- Person ---")
    Osoba1 = Person("Mike", 31)
    Osoba1.walk()
    Osoba1.say("Hello World")

    print("\n--- Superhero ---")
    superhero1 = Superhero("John", 25, "johny123")
    superhero1.use_super_sight()
    superhero1.walk(True)
    superhero1.fly()
    superhero1.walk()
    superhero1.say("Goodbye!")