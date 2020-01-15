print("into lua file\n")
function bab(filename, wordcount, ngrams)
    s = creadfile(filename)
    mstring = ''
    print("just before while loop in bab\n")
    while line do   -- tokenize, in a loop
        potstring, offset = ctokenize(filename, 0)
        mstring = mstring + potstring
        print(mstring)
    end
    print("just after while loop in bab")
    shingles(ngrams, offset)

end

function string.slice(tbl, first, last, step)
    print("made it into string.slice")
    local sliced = ''
    for i = first or 1, last or #tbl, step or 1 do
      sliced[#sliced+1] = tbl[i]
    end
    return sliced
end


function shingles (nngrams,offset) -- another lua function that shingles it called once to greate nngrams(list of 3 words)
    print("made it into shingles")
    stringShingles = {}
    local newstring = mstring
    newstring = newstring +  string.slice(mstring, mstring[1], mstring[nngrams])
    for i = 1, offset do
        stringShingles = string.slice(newstring, mstring[i], mstring[i+nngrams])
    end
end

function prefix (w1, w2)
    return w1 .. ' ' .. w2
    end
-- stringShingles is global
function lookuptable(offset, ngrams)   -- another lua function that sets up the lookup table turns shingles into lookup table 
    print("made it into lookuptable")
    table = {}
    for i = 1, offset do
        local shingle = stringShingles[i]
        table{[prefix(shingle[1],shingle[2])] = string.slice(shingle, shingle[3], shingle[ngrams])}
    end
    return table    -- lookup table: every possible two word prefix in a shingle is a key in the lookup table
end

-- another that babbles: randomly choosing an entry in the lookuptable
function babbler(table, wordcount) -- randomly select one of the entries from the value randomly that the key points to
    local finstring = ""
    print("made it into babbler")
    local r = table[math.random(#table)]  -- grabbing the first random key
    for i = 1, wordcount do
        w = table[math.random(table[r])]  -- grab subsequent random key
        r = table[w][math.random(#w)]   -- use that key to grab a random value
        finstring = finstring + r              -- save the random key into finstring
    end
    print(finstring)
end

-- need to finish the babbler, I don't think I am handling the keys vs values correctly on lines 48 and 49
