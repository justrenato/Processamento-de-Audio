all: wavinfo wavrev wavvol wavautovol wavecho wavwide wavcat wavmix

wavinfo:  filtros.c info.c filtros.h
			gcc -Wall filtros.c info.c -o wavinfo

wavrev: filtros.c rev.c filtros.h
			gcc -Wall filtros.c rev.c -o wavrev

wavvol: filtros.c vol.c filtros.h
			gcc -Wall filtros.c vol.c -o wavvol

wavautovol: filtros.c autoVol.c filtros.h
			gcc -Wall filtros.c autoVol.c -o wavautovol

wavecho:filtros.c echo.c filtros.h
			gcc -Wall filtros.c echo.c -o wavecho

wavwide:filtros.c wide.c filtros.h
			gcc -Wall filtros.c wide.c -o wavwide

wavcat:filtros.c cat.c filtros.h
			gcc -Wall filtros.c cat.c -o wavcat

wavmix:filtros.c mix.c filtros.h
			gcc -Wall filtros.c mix.c -o wavmix


clean:
	-rm *.o

purge: clean
	-rm wav*