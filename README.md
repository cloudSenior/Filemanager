При запуске, создаться папка в документах FAConfig

FAConfig создает вместе с собой файл config.cfg он содержит :

#modules: <ROOT> | Root он модули берет и корневой папки, то есть в FAConfig папке будет папка modules и от туда будет брать. но вы можете поменять папку задав другой путь.
#rootfilter: | Откуда будет сортировать файл	


--Формат создания модулей
#format: .exe .msi | Форматы, пишим их без лишних пробелов(Могут вызвать проблемы при лишнем пробели)
#where: | При нахождение файла будет переносить по данному пути.
