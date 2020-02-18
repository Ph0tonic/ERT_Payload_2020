# Config

IMPORTANT, voici les différnetes étapes pour configurer le raspberry PI.

1. Ajouter `enable_uart=1` dans le fichier `/boot/config.txt`
2. Ajouter l'utilisateur actuel dans les groups `dialout` and `tty` :

```sh
sudo usermod -a -G dialout username ; sudo usermod -a -G tty username
```

3. Aller dans les configurations du PI et dans `Interfaces` désactiver `Serial Console` mais laisser `Serial Port` activé. 
4. Redémarrer le raspberry pi afin que ces modifications soient prises en compte

# Sources

- https://elinux.org/RPi_Serial_Connection
- https://www.howtogeek.com/50787/add-a-user-to-a-group-or-second-group-on-linux/
- https://www.pjrc.com/teensy/td_uart.html

