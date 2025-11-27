from typing import List
from types import Position, ShipType, Direction, ShipTile, ShipState
from constants import TILE_SIZE

class Hitbox:
    def __init__(self, x: float, y: float, width: float, height: float):
        self.x = x
        self.y = y
        self.width = width
        self.height = height

    def update(self, pos: Position, width: float, height: float):
        self.x, self.y = pos.x, pos.y
        self.width, self.height = width, height

class Ship:
    def __init__(self, pos: Position, length: int, ship_type: ShipType, direction: Direction):
        self.pos = pos
        self.length = length
        self.type = ship_type
        self.direction = direction
        self.tiles: List[ShipTile] = [ShipTile(coords=Position(pos.x + i, pos.y)) for i in range(length)]
        self.hitbox = Hitbox(pos.x, pos.y, length * TILE_SIZE, TILE_SIZE)
        self.is_updating = False
        self.is_placed = False
        self.invalid_placement = False
        self.texture_states: dict[ShipState, str] = {
            ShipState.NORMAL: f"{ship_type.value}x1",
            ShipState.DAMAGED: f"{ship_type.value}x1_zepsuta"
        }
        self.current_state = ShipState.NORMAL

    def get_texture(self):
        return self.texture_states[self.current_state]



