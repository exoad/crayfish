import 'package:flutter/material.dart';

class SurfacePainter extends StatelessWidget {
  final void Function(Canvas, Size) paint;
  final Color backgroundColor;
  final Widget? child;

  const SurfacePainter({
    super.key,
    this.child,
    required this.paint,
    this.backgroundColor = Colors.white,
  });

  @override
  Widget build(BuildContext context) {
    return CustomPaint(painter: _(paint), child: child);
  }
}

class _ extends CustomPainter {
  final void Function(Canvas, Size) cb;

  _(this.cb);

  @override
  void paint(Canvas canvas, Size size) {
    cb(canvas, size);
  }

  @override
  bool shouldRepaint(covariant CustomPainter oldDelegate) {
    return false;
  }
}
