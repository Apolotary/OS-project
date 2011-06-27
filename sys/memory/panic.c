k_panic(str)
{
	k_puts("Kernel PANIC");
	k_puts(str);
	k_stop();
}
