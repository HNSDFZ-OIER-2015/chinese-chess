#
# Copyright 2016 HNSDFZ-OIER
#

import sys

import game
import resource

if __name__ != "__main__":
    raise RuntimeError("This is a application")

resource.load_resources()
instance = game.Game()

if len(sys.argv) > 1:
    try:
        command = sys.argv[1]
        address = sys.argv[2]
        port = int(sys.argv[3])
    except IndexError:
        print("Usage: main.py [create/join] [address] [port]")
        exit(1)

    if command == "create":
        game.setup_server(address, port)
    elif command == "join":
        game.setup_client(address, port)
    else:
        print("(error) Unknown command: %s" % command)
        exit(1)

instance.run()
