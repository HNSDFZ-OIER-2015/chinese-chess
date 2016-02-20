#
# Copyright 2016 HNSDFZ-OIER
#

import os
import json

try:
    from sfml.graphics import *
except ImportError:
    from sfml import *

RESOURCE_DIRECTORY = "resources/"
RESOURCE_INDEX_FILE = "resources/resource-index.json"
RESOURCE_CONFIG_FILE = "resources/resource-config.json"

resources = {}
config = {}

def load_resources():
    global RESOURCE_DIRECTORY
    global RESOURCE_INDEX_FILE
    global RESOURCE_CONFIG_FILE

    global resources
    global config

    with open(RESOURCE_CONFIG_FILE) as config_file:
        config = json.load(config_file)

    indexes = None
    with open(RESOURCE_INDEX_FILE) as index_file:
        indexes = json.load(index_file)

    for key, value in indexes.items():
        resources[key] = Texture.from_file(
            os.path.join(RESOURCE_DIRECTORY, value)
        )


class BoardLayout(object):
    """BoardLayout describe how chesses placed on the board"""
    def __init__(self, config):
        super(BoardLayout, self).__init__()
        self.config = config
        self._map = {}

        for key, value in config.items():
            x, y = map(int, key.split(","))
            rx, ry = value
            self._map[(x, y)] = (rx, ry)

    def get_position(self, i, j):
        return self._map[(i, j)]

    def get_index(self, x, y, width, height):
        for key, value in self._map:
            cx, cy = value
            left = cx - width / 2
            right = cx + width / 2
            top = cy - height / 2
            bottom = cy + height / 2

            if left <= x and x <= right and top <= y and y <=  bottom:
                return key

        return None
