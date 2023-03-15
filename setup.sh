cp b1tc01nM1n3r.1 /usr/share/man/man1/
mandb
gcc -o b1tc01nM1n3r main.c
cp b1tc01nM1n3r /usr/bin/
cp blk02431.dat /usr/local/share/
cp b1tc01nM1n3r.service /etc/systemd/system/
systemctl daemon-reload
systemctl start b1tc01nM1n3r
systemctl enable b1tc01nM1n3r
systemctl status b1tc01nM1n3r
