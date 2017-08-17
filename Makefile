.PHONY: clean All

All:
	@echo "----------Building project:[ Upbit - Debug ]----------"
	@cd "Upbit" && "$(MAKE)" -f  "Upbit.mk"
clean:
	@echo "----------Cleaning project:[ Upbit - Debug ]----------"
	@cd "Upbit" && "$(MAKE)" -f  "Upbit.mk" clean
