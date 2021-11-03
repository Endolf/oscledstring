import subprocess

revision = (
    subprocess.check_output(["git", "rev-parse", "HEAD"])
    .strip()
    .decode("utf-8")
)
tag = (
    subprocess.check_output(["git", "tag", "--points-at", "HEAD"])
    .strip()
    .decode("utf-8")
)
if(not tag):
    print("-DPIO_GIT_REV='\"%s\"'" % (revision))
else:
    print("-DPIO_GIT_REV='\"%s\"' -DPIO_GIT_TAGS='\"%s\"'" % (revision, tag))