import sys
import os

print(sys.argv)

BIG_PROMPT = """
Commands:
1) build and run
2) build
3) run
4) configure (CMake)
"""


def sh(shell_command: str):
    print(shell_command)
    os.system(shell_command)


def run():
    sh(r"out\build\Debug\program.exe")


def build():
    sh(r"cmake --build out\build")


def configure():
    sh(r"cmake -B out\build -S .")


def do(choice: int):
    if choice == 1:
        build()
        run()
    elif choice == 2:
        build()
    elif choice == 3:
        run()
    elif choice == 4:
        configure()
    else:
        print("bad option")
    pass


def main():
    if len(sys.argv) < 2:
        print(BIG_PROMPT)
        choice = input("-> ")
        do(int(choice))
    else:
        do(int(sys.argv[1]))
    pass

if __name__ == "__main__":
    main()