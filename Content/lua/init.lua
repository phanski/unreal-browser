-- require("Libraries.HttpClient")
client = get_module("HttpClient")
json = get_internal_module("json")
file_access = get_internal_module("files")


pass_control = nil

base_url = "http://127.0.0.1:8000/"

function Main(f)
    pass_control = f
    print("init")
    -- result = coroutine.wrap(function (url)
    --     return client.get(url)
    -- end)("http://127.0.0.1:8000/")


    -- local co = coroutine.create(function(param)
    --     local a=  client.get(param)
    --     print(a)
    -- end)

    -- -- Start the coroutine
    -- local success, result = coroutine.resume(co, "http://127.0.0.1:8000/")
    -- result = nil
    -- coroutine.wrap(function()
    --     print("sync wait 1 sec, start time: " .. os.time())
    --     result = sync(client.get)("http://127.0.0.1:8000/")
    --     print("sync wait 1 sec, done time: " .. os.time())
    -- end)()



    client.get(base_url.."index.json", LoadLuaFiles)
    
    
    -- print(result)
end

function LoadLuaFiles(result)
    jsondata = json.from_json(result)
    client.get(base_url..jsondata["required_files"][1], WriteLuaFiles)
end

function WriteLuaFiles(result)
    file_access.write_file("lua/External/Main.lua", result)
    pass_control()
end

return true