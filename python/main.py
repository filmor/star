import os
oldpath = os.getcwd()
os.chdir("python")

try:
    import sys, time, __main__, IPython

    IPython.Shell.IPShell(user_ns = __main__.__dict__).mainloop()

except:
    import sys, traceback

    traceback.print_exc(file=sys.stdout)
finally:
    os.chdir(oldpath)
