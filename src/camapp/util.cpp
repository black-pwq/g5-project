float clampToEdge(float val, float min, float max) {
	if(val < min) {
		val = min;
	} else if (val > max) {
		val = max;
	}
	return val;
}