
gEntities = 
{
    [0] = {
        type = "h",
        texture = "./assets/walk_cycle.bmp",
        width = 16,
        height = 24,
        frame = 8,
        tileX = 9,
        tileY = 2,
        facing = "l",
        layer = 0,
        anims = 
        {
            up    = {1, 2, 3, 4},     -- up
            right = {5, 6, 7, 8},     -- right
            down  = {9, 10, 11, 12},  -- down
            left  = {13, 14, 15, 16}, -- left
        },
        numberOfStates = 2,
        controller = {"wait", "move"},
        state = "wait"
    },
    [1] = {
        type = "n",
        texture = "./assets/walk_cycle.bmp",
        width = 16,
        height = 24,
        frame = 8,
        tileX = 9,
        tileY = 5,
        facing = "d",
        layer = 0,
        anims = 
        {
            up    = {1, 2, 3, 4},     -- up
            right = {5, 6, 7, 8},     -- right
            down  = {9, 10, 11, 12},  -- down
            left  = {13, 14, 15, 16}, -- left
        },
        numberOfStates = 2,
        controller = {"npc_stand"},
        state = "npc_stand"
    },
    [2] = {
        type = "n",
        texture = "./assets/walk_cycle.bmp",
        width = 16,
        height = 24,
        frame = 8,
        tileX = 3,
        tileY = 5,
        facing = "u",
        layer = 0,
        anims = 
        {
            up    = {1, 2, 3, 4},     -- up
            right = {5, 6, 7, 8},     -- right
            down  = {9, 10, 11, 12},  -- down
            left  = {13, 14, 15, 16}, -- left
        },
        numberOfStates = 2,
        controller = {"plan_stroll", "move"},
        state = "plan_stroll"
    },
    [3] = {
        type = "n",
        texture = "./assets/walk_cycle.bmp",
        width = 16,
        height = 24,
        frame = 8,
        tileX = 8,
        tileY = 9,
        facing = "l",
        layer = 0,
        anims = 
        {
            up    = {1, 2, 3, 4},     -- up
            right = {5, 6, 7, 8},     -- right
            down  = {9, 10, 11, 12},  -- down
            left  = {13, 14, 15, 16}, -- left
        },
        numberOfStates = 2,
        controller = {"plan_stroll", "move"},
        state = "plan_stroll"
    },
    [4] = {
        type = "n",
        texture = "./assets/walk_cycle.bmp",
        width = 16,
        height = 24,
        frame = 8,
        tileX = 9,
        tileY = 9,
        facing = "r",
        layer = 0,
        anims = 
        {
            up    = {1, 2, 3, 4},     -- up
            right = {5, 6, 7, 8},     -- right
            down  = {9, 10, 11, 12},  -- down
            left  = {13, 14, 15, 16}, -- left
        },
        numberOfStates = 2,
        controller = {"plan_stroll", "move"},
        state = "plan_stroll"
    },
    [5] = {
        type = "n",
        texture = "./assets/walk_cycle.bmp",
        width = 16,
        height = 24,
        frame = 8,
        tileX = 3,
        tileY = 4,
        facing = "d",
        layer = 0,
        anims = 
        {
            up    = {1, 2, 3, 4},     -- up
            right = {5, 6, 7, 8},     -- right
            down  = {9, 10, 11, 12},  -- down
            left  = {13, 14, 15, 16}, -- left
        },
        numberOfStates = 2,
        controller = {"plan_stroll", "move"},
        state = "plan_stroll"
    },
}
