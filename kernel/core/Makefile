#
# Copyright LemonClear
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

SUBDIRS         := 
source          := $(wildcard *.c)
objects         := $(patsubst %.c,%.o,$(source))


## main compile
PHONY:_all

_all:$(objects) $(SUBDIRS)

$(objects):%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDE_DIRS)
	mv $@ $(BUILD_OUTPUT)

$(SUBDIRS):trace
	+$(MAKE) -C $@

trace:
	@echo 'bengin compile...... $(SUBDIRS)'


clean:
	rm -rf $(objects)

.PHONY: $(PHONY)
