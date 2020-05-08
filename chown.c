#ifdef LS_EXEC
#include "user.h"

int main(int argc, char **argv) 
{
    char *path = argv[2];
    char *user = argv[1];
    char *group;
    int group_id, user_id, run;

    if (argc != 3) 
    {
        exit();
    }

    if ((group = strchr(argv[1], ':')))
    {
        *group = 0;
        group++;
    }

    printf(1, "user: %s\ngroup: %s\n", user, group);
    
    if(group)
    {
        gid_sekarang = cek_nama_group(group);
        
        if(gid_sekarang == 0)
        {
            printf(2, "Group %s tidak ditemukan\n", group);
            exit();
        }

        group_id = gid_sekarang->gid;
    }

    if(user[0])
    {
        uid_sekarang = cek_nama(user);

        if(uid_sekarang == 0)
        {
            printf(2, "User %s tidak ditemukan", user);
            exit();
        }

        user_id = uid_sekarang->uid_user;
    }   

    printf(1, "uid: %d\n\ngid: %d\n", user_id, group_id);

    exit();
}
