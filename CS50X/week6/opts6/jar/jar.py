class Jar:

    cookies = 0

    def __init__(self, capacity=12):
        self.total_capacity = capacity

    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        if self.size + n > self.total_capacity:
            raise ValueError
        self.cookies += n

    def withdraw(self, m):
        if self.size - m < 0:
            raise ValueError
        self.cookies -= m

    @property
    def capacity(self):
        return self.total_capacity

    @capacity.setter
    def capacity(self, new_capacity):
        self.total_capacity = new_capacity

    @property
    def size(self):
        return self.cookies

def main():
    jar = Jar()

    print("Jar Capacity is: " + str(jar.capacity))
    jar.deposit(6)
    print(str(jar))
    jar.withdraw(2)
    print(str(jar))


main()