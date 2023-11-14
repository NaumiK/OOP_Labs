set(LABLIST
  LAB1
  LAB2
  LAB3
  LAB4
  LAB5
  LAB6
  test
  )

foreach(LAB ${LABLIST})
  add_subdirectory(${LAB})
endforeach(LAB ${LABLIST})

set(LABLIST ${LABLIST} PARENT_SCOPE)
