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
  nextlayerid = 2,
  nextobjectid = 1,
  properties = {},
  tilesets = {
    {
      name = "room_tileset",
      firstgid = 1,
      filename = "../../HowToMakeAnRPG_Project/TilesFiles/room_tileset.tsx"
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
      name = "Tile Layer 1",
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
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        94, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 70,
        45, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66
      }
    }
  }
}
