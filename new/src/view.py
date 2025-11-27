import pygame
from model import Ship
class ShipRenderer:
    def __init__(self):
        self.textures: dict[str, pygame.Surface] = {}

    def load_textures(self):
        self.textures["ship_1_normal"] = (
            pygame.image.load("assets/ship1_normal.png"))
        self.textures["ship_1_damaged"] = (
            pygame.image.load("assets/ship1_damaged.png"))

    def render(self, ship: Ship, screen: pygame.Surface):
        texture_id = ship.get_texture()
        texture = self.textures.get(texture_id)
        if texture:
            screen.blit(texture, (ship.pos.x, ship.pos.y))

