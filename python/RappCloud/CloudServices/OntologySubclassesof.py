#!/usr/bin/env python


# Copyright 2016 RAPP

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

    #http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Authors: Konstantinos Panayiotou
# contact: klpanagi@gmail.com


## @file RappCloud/CloudServices/Service.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


##
#  @brief Face-Detection Cloud Service Class.
#  @param fast
#  @param image
#
class OntologySubclassesof(Service):
    def __init__(self, *args, **kwargs):
        # Cloud Service request arguments
        self.query = ''
        ###############################

        super(OntologySubclassesof, self).__init__(
            svcname='ontology_subclasses_of',
            **kwargs
            )


    ##
    #  @brief Create payload object of face_detection cloud service
    #
    def _make_payload(self):
        # Create and return payload object
        return Payload(query=self.query)


    ##
    #  @brief Create array of file object(s) of face_detection cloud service.
    #
    def _make_files(self):
        # Create and return array of file objects
        return []