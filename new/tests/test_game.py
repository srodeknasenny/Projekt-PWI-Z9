import unittest
from unittest.mock import Mock
from src.model import Ship, Hitbox, Position, ShipType, Direction, ShipTile, ShipState
from src.constants import TILE_SIZE

class TestShip(unittest.TestCase):
    def setUp(self):
        self.pos = Position(10.0, 20.0)
        self.ship = Ship(self.pos, length=3, ship_type=ShipType.SHIP_1, direction=Direction.HORIZONTAL)

    def test_init_tiles(self):
        self.assertEqual(len(self.ship.tiles), 3)
        self.assertEqual(self.ship.tiles[0].coords.x, 10.0)
        self.assertEqual(self.ship.tiles[2].coords.x, 30.0)  # 10 + 2*TILE_SIZE?

    def test_hitbox_init(self):
        self.assertEqual(self.ship.hitbox.x, 10.0)
        self.assertEqual(self.ship.hitbox.width, 3 * TILE_SIZE)

    def test_get_texture(self):
        self.assertEqual(self.ship.get_texture(), "ship_1x1")  # Sprawdź ShipType.value
        self.ship.current_state = ShipState.DAMAGED
        self.assertEqual(self.ship.get_texture(), "ship_1x1_zepsuta")

class TestHitbox(unittest.TestCase):
    def test_update(self):
        hitbox = Hitbox(0, 0, 10, 20)
        new_pos = Position(5, 5)
        hitbox.update(new_pos, 15, 25)
        self.assertEqual(hitbox.x, 5)
        self.assertEqual(hitbox.height, 25)

if __name__ == '__main__':
    unittest.main()
