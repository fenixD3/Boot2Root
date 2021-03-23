# Get Root from GRUB

We can show GRUB menu during launching Linux. We should press [SHIFT] key when system start.

[comment]: <> (include print screen with command output)

Further we launch general parent process, in Unix-like systems it is named "init":

    live init=/bin/bash

We use standard kernel function, launching init process, which start only from user with superuser access.  
Then check our user with `whoami`

[comment]: <> (include print screen with command output)

Yeah, we are root!