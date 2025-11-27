from enum import Enum, auto
from dataclasses import dataclass

class Direction(Enum):
    UP = auto()
    RIGHT = auto()
    DOWN = auto()
    LEFT = auto()

class GameState(Enum):
    GAME_START = auto()
    GAME_PREPARE_PLAYER_1 = auto()
    GAME_PREPARE_PLAYER_2 = auto()
    GAME_RUNNING = auto()
    GAME_PAUSED = auto()
    GAME_WON_PLAYER_1 = auto()
    GAME_WON_PLAYER_2 = auto()
    GAME_WON_AI = auto()

class ShipType(Enum):
    ONE_MASTED = auto()
    TWO_MASTED = auto()
    THREE_MASTED = auto()
    FOUR_MASTED = auto()

class ShipState(Enum):
    NORMAL = auto()
    DAMAGED = auto()
    INVALID_PLACEMENT = auto()

@dataclass
class Position:
    x: float
    y: float

@dataclass
class ShipTile:
    coords: Position
    got_shot: bool = False