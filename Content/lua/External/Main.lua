Actor = get_module("Actor")


function Main ()
    spawn_orbit_camera({X=0,Y=0,Z=100}, 100.0)

    CurrentActor = nil
    CurrentActorIndex = 0

    Choices = {
        [0] = function ()
            return Actor.SpawnGLTFAsset("cube.gltf", "CubeCube1", {X=0, Y=0, Z=50}, {X=.1, Y=.1, Z=.1})
        end,

        [1] = function ()
            return Actor.SpawnGLTFScene("gun/gun.gltf", "Gun", {X=0, Y=0, Z=50}, {X=1.5, Y=1.5, Z=1.5})

        end,

        [2] = function ()
            return Actor.SpawnGLTFScene("car2/car.gltf", "Car", {X=0, Y=0, Z=50}, {X=1, Y=1, Z=1})
        end
    }

    Actor.SpawnGLTFAsset("cube.gltf", "Pedestal", {X=0, Y=0, Z=0}, {X=.5, Y=.5, Z=.5})

    CurrentActor = Choices[0]()
    on_key_down("Left", function ()
        if (CurrentActorIndex > 0) then
            CurrentActor:Delete()
            CurrentActorIndex = CurrentActorIndex - 1
            CurrentActor = Choices[CurrentActorIndex]()
        end
    end)

    on_key_down("Right", function ()
        if (CurrentActorIndex < (#Choices)) then
            CurrentActor:Delete()
            CurrentActorIndex = CurrentActorIndex + 1
            CurrentActor = Choices[CurrentActorIndex]()
        end
    end)
end

return true