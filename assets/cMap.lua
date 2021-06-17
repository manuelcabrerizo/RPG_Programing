map = {
  version = "1.5",
  luaversion = "5.1",
  tiledversion = "1.7.0",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 12,
  height = 12,
  tilewidth = 16,
  tileheight = 16,
  nextlayerid = 3,
  nextobjectid = 1,
  properties = {},
  tilesets = {
    [0] = {
      name = "room_tileset",
      firstgid = 1,
      filename = "../../HowToMakeAnRPG_Project/TilesFiles/room_tileset.tsx"
    },
    [1] = {
      name = "collision_graphic",
      firstgid = 133,
      filename = "../../HowToMakeAnRPG_Project/TilesFiles/collision_graphic.tsx"
    }
  },
  layers = {
    [0] = {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 12,
      height = 12,
      id = 1,
      name = "base",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      encoding = "lua",
      data = {
        1, 4, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
        12, 15, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 73, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 73, 70,
        94, 83, 83, 83, 1, 7, 7, 11, 83, 83, 83, 70,
        94, 83, 83, 83, 23, 0, 0, 33, 83, 83, 83, 70,
        94, 83, 83, 83, 34, 0, 0, 44, 83, 83, 83, 70,
        94, 83, 83, 83, 45, 51, 51, 55, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        45, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66
      }
    },
    [1] = {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 12,
      height = 12,
      id = 2,
      name = "collition",
      visible = true,
      opacity = 0.35,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      encoding = "lua",
      data = {
        133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133,
        133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 0, 133,
        133, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 133,
        133, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 133,
        133, 0, 0, 0, 133, 133, 133, 133, 0, 0, 0, 133,
        133, 0, 0, 0, 133, 133, 133, 133, 0, 0, 0, 133,
        133, 0, 0, 0, 133, 133, 133, 133, 0, 0, 0, 133,
        133, 0, 0, 0, 133, 133, 133, 133, 0, 0, 0, 133,
        133, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 133,
        133, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 133,
        133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133,
        133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 0, 133
      }
    }
  }
}
