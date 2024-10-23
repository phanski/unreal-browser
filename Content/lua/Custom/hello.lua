function Main ()
    preload_assets("cube.gltf", "gun/gun.gltf", "car2/car.gltf")

    spawn_orbit_camera({X=0,Y=0,Z=100}, 100.0)
    
    CurrentActor = nil
    CurrentActorIndex = 0

    Choices = {
        [0] = function ()
            return spawn_actor({X=0, Y=0, Z=50}, {X=.1, Y=.1, Z=.1}, "cube.gltf", "CubeCube1")
        end,

        [1] = function ()
            return spawn_actor_scene({X=0, Y=0, Z=50}, {X=1.5, Y=1.5, Z=1.5}, "gun/gun.gltf", "Gun")

        end,

        [2] = function ()
            return spawn_actor_scene({X=0, Y=0, Z=50}, {X=1, Y=1, Z=1}, "car2/car.gltf", "Car")
        end
    }
    
    
    spawn_actor({X=0, Y=0, Z=0}, {X=.5, Y=.5, Z=.5}, "cube.gltf", "Pedestal")
    CurrentActor = Choices[0]()
    on_key_down("Left", function ()
        if (CurrentActorIndex > 0) then
            delete_actor(CurrentActor)
            CurrentActorIndex = CurrentActorIndex - 1
            CurrentActor = Choices[CurrentActorIndex]()
            
        end
        -- print(CurrentActorIndex)
    end) 

    on_key_down("Right", function ()
        if (CurrentActorIndex < (#Choices)) then
            delete_actor(CurrentActor)
            CurrentActorIndex = CurrentActorIndex + 1
            CurrentActor = Choices[CurrentActorIndex]()
        end
        -- print(CurrentActorIndex)
    end) 
end