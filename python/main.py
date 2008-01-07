import sys
sys.path += ['python']

try:
    # import Star

    from IPython.Shell import IPShellEmbed

    ipshell = IPShellEmbed()
    ipshell()

    from Star.Graphics import Scene, StarBackground, WaterGround

# \todo Setup standard scene:
#       - star background
#       - water ground
    base_scene = Scene()
    base_scene.background = StarBackground()
    base_scene.ground = WaterGround()
    base_scene()

    import main_menu

    raw_input()

except:
    import sys, traceback

    traceback.print_exc(file=sys.stdout)
