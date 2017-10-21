CFLAGS = -Wall

all: wavinfo wavrev wavvol wavautovol wavecho wavwide wavcat wavmix

wavinfo:  filtros.o info.o 
			gcc $(CFLAGS) filtros.o info.o -o wavinfo

wavrev: filtros.o rev.o 
			gcc $(CFLAGS) filtros.o rev.o -o wavrev

wavvol: filtros.o vol.o 
			gcc $(CFLAGS) filtros.o vol.o -o wavvol

wavautovol: filtros.o autoVol.o 
			gcc $(CFLAGS) filtros.o autoVol.o -o wavautovol

wavecho:filtros.o echo.o 
			gcc $(CFLAGS) filtros.o echo.o -o wavecho

wavwide:filtros.o wide.o 
			gcc $(CFLAGS) filtros.o wide.o -o wavwide

wavcat:filtros.o cat.o 
			gcc $(CFLAGS) filtros.o cat.o -o wavcat

wavmix:filtros.o mix.o 
			gcc $(CFLAGS) filtros.o mix.o -o wavmix


wavinfo.o:  filtros.c info.c filtros.h
			gcc $(CFLAGS) filtros.c info.c -o wavinfo

wavrev.o: filtros.c rev.c filtros.h
			gcc $(CFLAGS) filtros.c rev.c -o wavrev

wavvol.o: filtros.c vol.c filtros.h
			gcc $(CFLAGS) filtros.c vol.c -o wavvol

wavautovol.o: filtros.c autoVol.c filtros.h
			gcc $(CFLAGS) filtros.c autoVol.c -o wavautovol

wavecho.o:filtros.c echo.c filtros.h
			gcc $(CFLAGS) filtros.c echo.c -o wavecho

wavwide.o:filtros.c wide.c filtros.h
			gcc $(CFLAGS) filtros.c wide.c -o wavwide

wavcat.o:filtros.c cat.c filtros.h
			gcc $(CFLAGS) filtros.c cat.c -o wavcat

wavmix.o:filtros.c mix.c filtros.h
			gcc $(CFLAGS) filtros.c mix.c -o wavmix


clean:
	-rm *.o

purge: clean
	-rm wav*