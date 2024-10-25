httpmodule = {}

local client = get_internal_module("http")

function makeSync(asyncFn)
    return function(...)
        local result
        local co = coroutine.create(function(...)
            local waitForCallback = coroutine.yield()  -- First yield returns the wait function
            result = waitForCallback()  -- Second yield will get the actual result
        end)
        
        -- Start the coroutine
        coroutine.resume(co, ...)
        
        -- Create a function that will yield until the callback is called
        local function waitForCallback()
            return coroutine.yield()
        end
        
        -- Resume with the wait function
        coroutine.resume(co, waitForCallback)
        
        -- Call the async function with our own callback
        asyncFn(..., function(response)
            coroutine.resume(co, response)
        end)
        
        return result
    end
end

-- httpmodule.get = makeSync(function (url)
--     local co = coroutine.running()  -- Get the current coroutine
--     local result
--     print("Url in module: "..url)
--     client.get(url, function (response)
--         result = response
--         coroutine.resume(co)
--     end)
--     coroutine.yield() 
--     return result
-- end)

function httpmodule.get(url, callback)
    client.get(url, callback)
end



return httpmodule