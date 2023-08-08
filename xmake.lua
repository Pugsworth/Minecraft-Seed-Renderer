add_rules("mode.debug", "mode.release")

set_runtimes("MD") -- Use the dynamic runtime library on Windows

add_requires(
    "libspng 0.7.1",
    "olive.c >=2022.12.14"
)
add_requires(
    "lua 5.4.4", {configs = {shared = true}}
)

target("mc_seed_renderer")
    set_kind("binary")
    set_languages("c11")
    set_warnings("all")

    add_files("src/*.c")
    add_includedirs("include")
    add_includedirs("lib/libcubiomes") -- Not sure why I have to do this if it's already a dependency...

    if is_plat("windows") then
        add_syslinks("winmm")
    end

    add_deps("libcubiomes")

    add_packages(
        "libspng",
        "olive.c",
        "lua"
    )

    set_optimize("fastest")

    after_build(function(target)
        -- Copy the assets to the build binary directory
        os.cp("$(projectdir)/assets", "$(buildir)/$(plat)/$(arch)/$(mode)/")
    end)
target_end()

target("libcubiomes")
    set_kind("static")
    add_files("lib/libcubiomes/*.c")
    remove_files("lib/libcubiomes/tests.c")
    add_includedirs("lib/libcubiomes")
target_end()



--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

