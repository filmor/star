import sys
sys.path += ['python']

try:
    # import Star

#    from IPython.Shell import IPShellEmbed

#    ipshell = IPShellEmbed()
#    ipshell()

#    from Star.Graphics import Scene, StarBackground, WaterGround

# \todo Setup standard scene:
#       - star background
#       - water ground
#    base_scene = Scene()
#    base_scene.background = StarBackground()
#    base_scene.ground = WaterGround()
#    ScreenManager.background = base_scene

    from Screens import Menu

    main_menu = Menu("Star",
                    [
                        ("Play", PlayMenu),
                        ("Settings", SettingsMenu),
                        ("Quit", lambda : sys.exit(0)),
                    ]
                    )
    
    main_menu()

except:
    import sys, traceback

    traceback.print_exc(file=sys.stdout)
