import "package:flutter/material.dart";
import "package:flutter/services.dart";

void main() {
  runApp(const MapEditorApp());
}

class MapEditorApp extends StatelessWidget {
  const MapEditorApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "Crayfish Mapper",
      theme: ThemeData(
        primarySwatch: Colors.amber,
        colorScheme: ColorScheme.fromSwatch(primarySwatch: Colors.amber),
        useMaterial3: true,
        elevatedButtonTheme: const ElevatedButtonThemeData(
          style: ButtonStyle(
            shape: WidgetStatePropertyAll<RoundedRectangleBorder>(RoundedRectangleBorder()),
            foregroundColor: WidgetStatePropertyAll<Color>(Colors.black),
          ),
        ),
      ),
      home: const MapEditor(),
      debugShowCheckedModeBanner: false,
    );
  }
}

const int mapWidth = 24;
const int mapHeight = 24;

const int sAir = 0x01;
const int sWallBlue = 0x10;
const int sWallRed = 0x20;
const int sWallGreen = 0x30;

class MapEditor extends StatefulWidget {
  const MapEditor({super.key});

  @override
  State<MapEditor> createState() => _MapEditorState();
}

class _MapEditorState extends State<MapEditor> {
  late List<List<int>> mapData;
  int selectedSurfaceType = sWallBlue;

  static const double cellSize = 20.0;
  static const double cellPadding = 1.0;

  @override
  void initState() {
    super.initState();
    _initializeMap();
  }

  void _initializeMap() {
    mapData = <List<int>>[
      <int>[
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sWallRed,
        sWallRed,
        sWallRed,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sWallRed,
        sAir,
        sWallRed,
        sAir,
        sWallGreen,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sWallRed,
        sWallRed,
        sWallRed,
        sAir,
        sWallGreen,
        sAir,
        sWallGreen,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallGreen,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallGreen,
        sWallGreen,
        sWallGreen,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        8000,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sAir,
        sWallBlue,
      ],
      <int>[
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
        sWallBlue,
      ],
    ];
  }

  Color _getSurfaceColor(int surfaceType) {
    switch (surfaceType) {
      case sAir:
        return Colors.white;
      case sWallBlue:
        return const Color.fromARGB(255, 0, 0, 255);
      case sWallRed:
        return const Color.fromARGB(255, 255, 0, 0);
      case sWallGreen:
        return const Color.fromARGB(255, 0, 255, 0);
      default:
        return const Color.fromARGB(255, 255, 0, 255);
    }
  }

  String _getSurfaceName(int surfaceType) {
    switch (surfaceType) {
      case sAir:
        return "Air";
      case sWallBlue:
        return "Blue Wall";
      case sWallRed:
        return "Red Wall";
      case sWallGreen:
        return "Green Wall";
      default:
        return "Special";
    }
  }

  void _onCellTap(int x, int y) {
    setState(() {
      mapData[y][x] = selectedSurfaceType;
    });
  }

  void _clearMap() {
    setState(() {
      for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
          mapData[y][x] = sAir;
        }
      }
    });
  }

  void _fillBorder() {
    setState(() {
      for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
          if (x == 0 || x == mapWidth - 1 || y == 0 || y == mapHeight - 1) {
            mapData[y][x] = sWallBlue;
          }
        }
      }
    });
  }

  String _generateCCode() {
    final StringBuffer buffer = StringBuffer();
    buffer.writeln("static const I32 worldMap[MAP_WIDTH][MAP_HEIGHT] =");
    buffer.writeln("{");
    for (int y = 0; y < mapHeight; y++) {
      buffer.write("    { ");
      for (int x = 0; x < mapWidth; x++) {
        final int value = mapData[y][x];
        String valueStr;
        switch (value) {
          case sAir:
            valueStr = "S_AIR";
            break;
          case sWallBlue:
            valueStr = "S_WALL_BLUE";
            break;
          case sWallRed:
            valueStr = "S_WALL_RED";
            break;
          case sWallGreen:
            valueStr = "S_WALL_GREEN";
            break;
          default:
            valueStr = value.toString();
        }
        buffer.write(valueStr);
        if (x < mapWidth - 1) {
          buffer.write(", ");
        }
      }
      buffer.write(" }");
      if (y < mapHeight - 1) {
        buffer.write(",");
      }
      buffer.writeln();
    }

    buffer.writeln("};");
    return buffer.toString();
  }

  void _showCodeDialog() {
    showDialog(
      context: context,
      builder: (BuildContext context) => AlertDialog(
        title: const Text("Generated C Code"),
        content: SizedBox(
          width: double.maxFinite,
          height: 400,
          child: SingleChildScrollView(
            child: SelectableText(
              _generateCCode(),
              style: const TextStyle(fontFamily: "Monospace", fontSize: 12),
            ),
          ),
        ),
        actions: <Widget>[
          TextButton(
            onPressed: () {
              Clipboard.setData(ClipboardData(text: _generateCCode()));
              ScaffoldMessenger.of(
                context,
              ).showSnackBar(const SnackBar(content: Text("Copied to Clipboard!")));
            },
            child: const Text("Copy"),
          ),
          TextButton(onPressed: () => Navigator.of(context).pop(), child: const Text("Close")),
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.black,
      body: Row(
        children: <Widget>[
          Container(
            width: 200,
            padding: const EdgeInsets.all(16),
            color: Colors.black,
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: <Widget>[
                const Text(
                  "Surfaces",
                  style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold, color: Colors.white),
                ),
                const SizedBox(height: 16),
                ...(<int>[sAir, sWallBlue, sWallRed, sWallGreen].map(
                  (int type) => Padding(
                    padding: const EdgeInsets.only(bottom: 8),
                    child: InkWell(
                      onTap: () => setState(() => selectedSurfaceType = type),
                      child: Container(
                        padding: const EdgeInsets.all(12),
                        decoration: BoxDecoration(
                          color: selectedSurfaceType == type ? Colors.blue.shade100 : Colors.white,
                          borderRadius: BorderRadius.circular(0),
                        ),
                        child: Row(
                          children: <Widget>[
                            Container(
                              width: 20,
                              height: 20,
                              decoration: BoxDecoration(
                                color: _getSurfaceColor(type),
                                border: Border.all(color: Colors.black),
                              ),
                            ),
                            const SizedBox(width: 8),
                            Text(_getSurfaceName(type)),
                          ],
                        ),
                      ),
                    ),
                  ),
                )),
                const SizedBox(height: 24),
                const Text(
                  "Controls",
                  style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold, color: Colors.white),
                ),
                const SizedBox(height: 16),
                ElevatedButton(onPressed: _clearMap, child: const Text("Clear Map")),
                const SizedBox(height: 8),
                ElevatedButton(onPressed: _fillBorder, child: const Text("Fill Border")),
                const SizedBox(height: 8),
                ElevatedButton(onPressed: _showCodeDialog, child: const Text("Export C Code")),
              ],
            ),
          ),
          Expanded(
            child: SingleChildScrollView(
              scrollDirection: Axis.horizontal,
              child: SingleChildScrollView(
                scrollDirection: Axis.vertical,
                child: Padding(
                  padding: const EdgeInsets.all(16),
                  child: SizedBox(
                    width: mapWidth * (cellSize + cellPadding) - cellPadding,
                    height: mapHeight * (cellSize + cellPadding) - cellPadding,
                    child: GridView.builder(
                      shrinkWrap: true,
                      physics: const NeverScrollableScrollPhysics(),
                      gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                        crossAxisCount: mapWidth,
                        crossAxisSpacing: cellPadding,
                        mainAxisSpacing: cellPadding,
                      ),
                      itemCount: mapWidth * mapHeight,
                      itemBuilder: (BuildContext context, int index) {
                        final int x = index % mapWidth;
                        final int y = index ~/ mapWidth;
                        final int surfaceType = mapData[y][x];
                        return GestureDetector(
                          onTap: () => _onCellTap(x, y),
                          child: Container(
                            decoration: BoxDecoration(
                              color: _getSurfaceColor(surfaceType),
                              border: Border.all(color: Colors.white30),
                            ),
                            child: surfaceType != sAir && surfaceType > 1000
                                ? Center(
                                    child: Text(
                                      surfaceType.toString(),
                                      style: const TextStyle(fontSize: 8),
                                    ),
                                  )
                                : null,
                          ),
                        );
                      },
                    ),
                  ),
                ),
              ),
            ),
          ),
        ],
      ),
    );
  }
}
