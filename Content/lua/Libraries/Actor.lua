local cmodule = get_internal_module("Actor")

local ActorModule = {}

local GameActor = {ref = nil}

function GameActor:New()
    o = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function GameActor:Delete()
    cmodule.delete_actor(self.ref)
end


function ActorModule.SpawnGLTFScene(AssetName, ActorName, Location, Scale)
    local newactor = GameActor:New()
    newactor.ref = cmodule.spawn_actor_scene(Location, Scale, AssetName, ActorName)
    return newactor
end


function ActorModule.SpawnGLTFAsset(AssetName, ActorName, Location, Scale)
    local newactor = GameActor:New()
    newactor.ref = cmodule.spawn_actor(Location, Scale, AssetName, ActorName)
    return newactor
end


return ActorModule